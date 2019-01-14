<?php

/**
 * This class is responsible for for interacting with the Civicrm CiviDiscount
 * Extension and its API's
 * certain routes
 */
class CiviDiscount {

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
}
