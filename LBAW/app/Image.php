<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Image extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'image';

  protected $fillable = [
    'url',
  ];

  public function getId(){
    return $this->id;
  }
}
