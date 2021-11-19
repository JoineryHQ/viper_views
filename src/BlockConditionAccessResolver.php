<?php

namespace Drupal\viper_views;

/**
 * Description of BlockConditionAccessResolver
 *
 * @author as
 */

class BlockConditionAccessResolver {
  use \Drupal\Core\Condition\ConditionAccessResolverTrait;

  /**
   * Conditions to be checked.
   * @var Array
   */
  private $conditions = [];

  /**
   * Constructor.
   * @param \Drupal\block\Entity\Block $block
   */
  public function __construct(\Drupal\block\Entity\Block $block) {
    foreach ($block->getVisibilityConditions() as $condition_id => $condition) {
      if ($condition_id != 'request_path') {
        $this->conditions[$condition_id] = $condition;
      }
    }
  }

  /**
   * Resolve conditions using ConditionAccessResolverTrait.
   * @return Boolean
   */
  public function resolve() {
    $ret = $this->resolveConditions($this->conditions, 'and');
    return $ret;
  }
}