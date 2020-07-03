<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Review extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'review';

  public function buyer(){
    return $this->belongsTo('App\User', 'buyer_id');
  }

  public function seller(){
    return $this->belongsTo('App\User', 'seller_id');
  }
}
