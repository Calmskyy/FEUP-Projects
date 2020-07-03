<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class ImageItem extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'image_item';

  protected $primaryKey = 'image_id';

  protected $fillable = [
    'image_id', 'item_id',
  ];

  public function item(){
    return $this->belongsTo('App\Item', 'item_id');
  }

  public function image(){
    return $this->belongsTo('App\Image', 'image_id');
  }
}
