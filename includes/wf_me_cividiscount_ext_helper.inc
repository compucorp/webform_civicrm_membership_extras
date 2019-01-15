<?php

/**
 * This class is responsible for for interacting with the Civicrm CiviDiscount
 * Extension and its API's
 * certain routes
 */
class wf_me_cividiscount_ext_helper {

  /**
   * Checks whether this extension is enabled or not.
   *
   * @return bool
   */
  public function isEnabled() {
    $isEnabled = CRM_Core_DAO::getFieldValue(
      'CRM_Core_DAO_Extension',
      'org.civicrm.module.cividiscount',
      'is_active',
      'full_name'
    );

    return !empty($isEnabled) ? TRUE : FALSE;
  }

  /**
   * Gets the details for the discount code using CiviDiscount API
   *
   * @param string $discountCode
   *
   * @return array
   */
  public function getDiscountCodeDetails($discountCode) {
    $result = civicrm_api3('DiscountCode', 'get', [
      'code' => $discountCode,
      'sequential' => 1
    ]);

    if ($result['count'] == 1) {
      return $result['values'][0];
    }
  }
}
