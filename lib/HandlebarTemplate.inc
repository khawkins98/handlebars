<?php
/**
 * @file
 * File for HandlebarTemplate class.
 */

/**
 * Handlers functionality for handlebar template files.
 */
class HandlebarTemplate {
  /**
   * Prints the content of the template file.
   */
  private $content;
   
  /**
   * Template file name, including extension.
   */
  private $template;

  /**
   * Full file path and file name.
   */
  private $file;

  /**
   * File path relative to Drupal root.
   */
  private $path;

  /**
   * Calculated value from filename without .tpl.hbr.
   */
  private $id;

  /**
   * Array of data from arguments.
   */
  private $info;

  /**
   * Related Handlebars JS file.
   */
  private $script;

  public function __construct($args = array()) {
    $this->info = (Object) $args;
  }

  /**
   * Check to see the file exists.
   */
  public function fileCheck($fileToCheck) {
    // Check bowith DRUPAL_ROOT and without as we don't need DRUPAL_ROOT for JS.
    // ToDo: Probably a more elegant way to structure this.
    if ( (!file_exists($fileToCheck)) && (!file_exists(DRUPAL_ROOT . '/' . fileToCheck)) )  {
      drupal_set_message(t('File !file does not exist', array('!file' => $fileToCheck)), 'error');
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Load Handlebars core functionality.
   */
  protected function load() {
    static $loaded;
    if (!$loaded) {
      if (!drupal_add_library('handlebars', 'drupal')) { 
        drupal_set_message(t('Handlebars library not properly configured / installed.'), 'error');
      }
      $loaded = TRUE;
    }
    $this->file();
    $this->script();
  }

  /**
   * Get statically cached template file name with extension.
   */
  protected function template() {
    if (!$this->template) {
      $this->template = (strpos($this->info->template, HANDLEBARS_EXT) !== FALSE)
        ? $this->info->template
        : $this->info->template . '.tpl.' . HANDLEBARS_EXT;
    }
    return $this->template;
  }

  /**
   * Calculate id from filename.
   */
  protected function id() {
    if (!$this->id) {
      $this->id = (strpos($this->info->template, HANDLEBARS_EXT) !== FALSE)
        ? str_replace('.tpl.' . HANDLEBARS_EXT, '', $this->info->template)
        : $this->info->template;
    }
    return $this->id;
  }

  /**
   * Full file path and filename.
   */
  protected function file() {
    if (!$this->file) {
      $this->file = DRUPAL_ROOT . '/' . $this->info->path . '/' . $this->info->template;
    }
    return $this->file;
  }

  /**
   * Full file path and filename to Handlebars JS file. 
   * Should be same name as template but with .js, i.e. handlebars_demo_page.tpl.hbr -> handlebars_demo_page.hbr.js
   * Optional.
   */
  protected function script() {
    $this->script = $this->info->path . '/' . str_replace('tpl.hbr', 'hbr.js', $this->info->template);

    return $this->script;
  }

  /**
   * Get file content.
   */
  protected function content() {
    if (!$this->content) {
      $this->content = ($this->fileCheck($this->file)) ? file_get_contents($this->file()) : '';
    }
    return $this->content;
  }

  /**
   * Main function: adds current template file to registry.
   */
  public function addTemplate(&$handlebars) {
    $this->load();
    if ($this->fileCheck($this->file)) {
      $handlebars[$this->id()] = $this;
    }
    $setting = array('handlebars' => array(
      'inventory' => array($this->id => $this->id),
    ));
    drupal_add_js($setting, 'setting');

    if ($this->fileCheck($this->script)) {
      drupal_add_js($this->script, 'file');
    }
  }

  /**
   * Displays template file with script tags.
   */
  public function render() {
    $attributes = array(
      'type' => 'text/x-handlebars-template',
      'id' => str_replace('.hbr','',$this->id()),
    );

    $output = '<script' . drupal_attributes($attributes) . '>';
    $output .= $this->content();
    $output .= '</script>';

    return $output;
  }
}
