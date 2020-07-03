<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class ImageUser extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'image_user';

  protected $primaryKey = 'image_id';

  protected $fillable = [
    'image_id', 'user_id',
  ];
  
  public function owner(){
    return $this->belongsTo('App\User', 'user_id');
  }

  public function image(){
    return $this->belongsTo('App\Image', 'image_id');
  }
}
