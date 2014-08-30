Handlebars for Drupal
=====================

Module adds tools to help integrate [Handlebars.js](http://handlebarsjs.com/) symantic templating with Druapl, and in a Drupal-like fashion.

Note
----

This is a fork from https://www.drupal.org/project/handlebars . To my knowlege that was all done by user asherry. It's entirely possible you should use that version instead. Ideally these edits will be pulled upstream.

Instructions
------------

1. Add this to your site's modules directory.
2. Add the [handlebars.js file](http://handlebarsjs.com/) to your libraries/handlebars directory (i.e. /sites/all/libraries/handlebars/handlebars-v1.3.0.js )
3. Enable this module.
4. Do code stuff or check out the sample module.

To do
-----

Here are my plans.

* DONE - Sample page: Add a sample module that loads fixed or remote content to a Drupal page.
* Sample block: Add a sample module that loads fixed or remote content as a Drupal block.
* Sample pane: Add a sample module that loads fixed or remote content as a Panels pane.
* Reusable Handlebar helpers: Add a central way to manage Handlebar helper functions.
* Reusable code all over: Make a way to be able to create a block, pane, or page in a easy fashion from the Drupal admin interface. Perhaps with ctools, but that may be overkill.
  * DONE - Autodetect JS: When loading sample.tpl.hbr, module will now check for and load any sample.hbr.js in the same directory.