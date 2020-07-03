<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Bid extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'bid';


  protected $fillable = [
    'bidder_id', 'item_id', '"date"'
];

  public function getId(){
    return $this->id;
  }

  public function owner(){
    return $this->belongsTo('App\User', 'bidder_id');
  }
}