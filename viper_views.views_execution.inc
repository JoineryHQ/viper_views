<?php
use Drupal\views\ViewExecutable;
use Drupal\views\Plugin\views\query\QueryPluginBase;

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
