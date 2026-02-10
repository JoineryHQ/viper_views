<?php
use Drupal\views\ViewExecutable;
use Drupal\views\Plugin\views\query\QueryPluginBase;
use Drupal\viper_views\BlockConditionAccessResolver;

/**
 * Implements hook_views_pre_render().
 */
function viper_views_views_pre_render(ViewExecutable $view) {
  // Load settings for this module, which are probably in drupal's settings.php.
  $settings = \Drupal::config('viper_views')->get();
  // If certain settings are defined, and if they match attributes of this view,
  // we'll take action.
  if (
    // If we're configured to display a certain block.
    !empty($settings['teachingResourcesAccessWarningBlockId'])
    // If we're configured for a certain view, and this is that view.
    && !empty($settings['teachingResourcesViewId'])
    && $view->id() == $settings['teachingResourcesViewId']
    // If we're configured for a certain view display, and this is that view display.
    && !empty($settings['teachingResourcesViewDisplayId'])
    && $view->getDisplay()->display['id'] == $settings['teachingResourcesViewDisplayId']
    // If we're configured to check the value of a certain view filter, and that filter has submitted values.
    && !empty($settings['teachingResourcesContentTypeFilterName'])
    && is_array($view->exposed_raw_input[$settings['teachingResourcesContentTypeFilterName']])
    // If we're configured to check that filter for a certain value, and that filter has this value.
    && !empty($settings['teachingResourcesContentTypeProblemSetValue'])
    && in_array($settings['teachingResourcesContentTypeProblemSetValue'], $view->exposed_raw_input[$settings['teachingResourcesContentTypeFilterName']])
  ) {

    // Load the block.
    $block = \Drupal\block\Entity\Block::load($settings['teachingResourcesAccessWarningBlockId']);

    // If this block is capable of being displayed on the page (with NO REGARD
    // for the block's request_path configuration), then display it here.
    // We do our own condition checking here because we have found no way to
    // bypass request_path config via hooks -- i.e., if the block is not configured
    // to display on the current page, then $block->access()->isAllowed() will
    // always return false.
    $resolver = new BlockConditionAccessResolver($block);
    if ($resolver->resolve()) {
      // Prepend the block to the top of the views output.
      $view->attachment_before = \Drupal::service('entity_type.manager')->getViewBuilder('block')->view($block);
    }
  }
}

/**
 * Implements hook_views_query_alter().
 */
function viper_views_views_query_alter(ViewExecutable $view, QueryPluginBase $query) {
  if ($view->id() == 'my_draft_content' &&
    (
      $view->getDisplay()->display['id'] == 'page_draft_primary_or_additional_author'
      || $view->getDisplay()->display['id'] == 'page_published_primary_or_additional_author'
    )
  ) {
    // Change the join to a LEFT join if it's an INNER join.
    $table = $query->getTableInfo('users_field_data_node__field_addl_authors__users');
    if (isset($table['join']->type) && $table['join']->type === "INNER") {
      //Change your Join type;
      $table['join']->type = 'LEFT';
    }
  }
}
