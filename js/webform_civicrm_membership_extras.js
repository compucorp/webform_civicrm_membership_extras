/**
 * @file
 * JavaScript .
 */

 (function ($) {
  Drupal.behaviors.acu_webform_draft_group = {
    attach: function (context, settings) {
      
      let moveGroupDiscountFields = () => {
        let discountCodeField = $('.webform-component--webform-discount-code-field')
        let group = $('#edit-submitted-webform-discount-code-all-fields-wraper')
        let discountCodeMessage = $('#discount-code-message-wrapper')
        let discountCodeActions = $('#discount-code-actions')

        if (group.length < 0) {
          return
        }

        discountCodeField.appendTo(group)
        discountCodeMessage.appendTo(group)
        discountCodeActions.appendTo(group)
      }

      moveGroupDiscountFields()
    }
  }
})(jQuery);
