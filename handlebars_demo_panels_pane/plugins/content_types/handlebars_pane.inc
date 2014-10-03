<?php

// Automatically detect module name. 
// Requires that this be two subdirectories under the main module.
$module_name = end(array_slice(explode('/',dirname(__FILE__)),-3,1));
$include_name = basename(__FILE__, '.inc');

$plugin = array(
  'single' => TRUE,
  'title' => t('Handlebars demo panel pane'),
  'description' => t('Integrate dynamic content via Handlebars.'),
  'category' => t('Handlebars'),
  'edit form' => $module_name . '_' . $include_name,
  'render callback' => $module_name . '_' . $include_name . '_render',
  'admin info' => $module_name . '_'  . $include_name . '_info',
  'defaults' => array(),
  'all contexts' => TRUE,
);

/**
 * Edit form.
 */
function handlebars_demo_panels_pane_handlebars_pane($form, &$form_state) {
 $conf = $form_state['conf'];

 $form['message'] = array(
   '#type' => 'textfield',
   '#title' => t('Loading message'),
   '#description' => t('Any loading message while Backbone pulls the content.'),
   '#default_value' => $conf['message'],
 );

 return $form;
}

/**
 * Edit form submit function.
 */
function handlebars_demo_panels_pane_handlebars_pane_submit($form, &$form_state) {
  $form_state['conf']['message'] = $form_state['values']['message'];
}

/**
 * Render the panel.
 */
function handlebars_demo_panels_pane_handlebars_pane_render($subtype, $conf, $args, $contexts) {
  if ($context->empty) {
    return;
  }

  handlebars_add_template(array(
      'template' => 'handlebars_demo_page.tpl.hbr',
      'path' => drupal_get_path('module', 'handlebars_demo_page'),
  ));

  $block->content = '<div class="handlebars-content-target">' . $conf['message'] . '</div>';
  return $block;

}

/**
 * Admin info.
 */
function handlebars_demo_panels_pane_handlebars_pane_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $content = '<p><b>Loading message:</b> ' . $conf['message'] . '</p>';

    $block = new stdClass;
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    $block->content = $content;
    return $block;
  }
}