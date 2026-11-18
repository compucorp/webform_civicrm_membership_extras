<?php

/**
 * Decides which existing memberships a webform submission may renew, based on
 * Membership Extras' 'membershipextras_webform_existing_membership_mode'.
 *
 * Pure logic: no CiviCRM calls, so it can be unit tested.
 */
class wf_me_renewable_memberships_filter {

  // These mirror CRM_MembershipExtras_SettingsManager::WEBFORM_MODE_*; kept
  // separate so this class stays pure and unit-testable.
  const MODE_RENEW = 'renew';
  const MODE_NEW_IF_NOT_CURRENT = 'new_if_not_current';
  const MODE_NEW_IF_NOT_CURRENT_AND_ENDED = 'new_if_not_current_and_ended';

  /**
   * Returns the memberships that may still be renewed, keeping keys and order.
   *
   * @param array $memberships
   *   Rows from wf_crm_webform_base::findMemberships(); each has 'status_id'
   *   and optionally 'end_date' (Y-m-d, may include a time, empty = lifetime).
   * @param string $mode
   *   One of the MODE_* constants; anything else behaves like MODE_RENEW.
   * @param int[] $currentStatusIds
   *   Status IDs whose is_current_member flag is set.
   * @param int[] $pendingStatusIds
   *   Status IDs named 'Pending' (never removed, so a retried sign-up reuses it).
   * @param string $today
   *   Today's date, Y-m-d.
   *
   * @return array
   *   The memberships that may still be renewed, with their original keys and
   *   order.
   */
  public function filter(array $memberships, $mode, array $currentStatusIds, array $pendingStatusIds, $today) {
    if ($mode !== self::MODE_NEW_IF_NOT_CURRENT && $mode !== self::MODE_NEW_IF_NOT_CURRENT_AND_ENDED) {
      return $memberships;
    }

    $keep = array_map('intval', array_merge($currentStatusIds, $pendingStatusIds));

    return array_filter($memberships, function ($membership) use ($mode, $keep, $today) {
      if (in_array((int) $membership['status_id'], $keep, TRUE)) {
        return TRUE;
      }
      if ($mode === self::MODE_NEW_IF_NOT_CURRENT) {
        return FALSE;
      }

      // Lifetime memberships (no end date) never count as ended. The empty()
      // guard matters: in PHP '' < '2026-11-17' is TRUE.
      $hasEnded = !empty($membership['end_date']) && substr($membership['end_date'], 0, 10) < $today;

      return !$hasEnded;
    });
  }

}
