<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class ItemHistory extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'item_history';


  protected $fillable = [
    'buyer_id', 'seller_id', 'title', 'reviewed'
];

  /*public function getId(){
    return $this->id;
  }*/

  public function buyer(){
    return $this->belongsTo('App\User', 'buyer_id');
  }

  public function seller(){
    return $this->belongsTo('App\User', 'seller_id');
  }

  public function imagesItem(){
    return $this->hasMany('App\ImageItem');
  }
}