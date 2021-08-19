# Viper Views: Custom code-based alterations of Drupal views


Developed for: IonicViper.org.

Author: Allen Shaw, Joinery

Licensed under [GNU GENERAL PUBLIC LICENSE, Version 2](LICENSE.txt)

## Functionality

* In a view named `my_draft_content`, in the display named `page_draft_primary_or_additional_author`, the `INNER JOIN`
  of the table `users_field_data_node__field_addl_authors__users` is changed to a `LEFT JOIN`.  Without this change,
  the view, as build in Drupal Views, excludes any nodes that have no additional authors, even if the primary author
  is the current user; with this change, the view includes such nodes.

## Support
![Joinery](/images/joinery-logo.png)

Joinery provides services for Drupal and CiviCRM including custom extension development, training, data migrations, and
more. We aim to keep this project in good working order, and will do our best to respond appropriately to issues reported
on its [github issue queue](https://github.com/JoineryHQ/viper_views/issues). In addition, if you require urgent or
highly customized improvements to this extension, we may suggest conducting a fee-based project under our standard
commercial terms.  In any case, the place to start is the [github issue queue](https://github.com/JoineryHQ/viper_views/issues) --
let us hear what you need and we'll be glad to help however we can.

And, if you need help with any other aspect of Drupal or CiviCRM -- from hosting to custom development to strategic consultation
and more -- please contact us directly via https://joineryhq.com