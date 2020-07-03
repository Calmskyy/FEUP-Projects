<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Item extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'item';

  protected $fillable = [
    'title', 'description', 'type', 'seller_id', 'start_time', 'stopped'
];

  public function getId(){
    return $this->id;
  }

  public function owner(){
    return $this->belongsTo('App\User', 'seller_id');
  }

  public function imagesItem(){
    return $this->hasMany('App\ImageItem');
  }
}
