<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class ItemAuction extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'auction_item';

  protected $primaryKey = 'item_id';

  protected $dates = ['end_time'];

  protected $fillable = [
    'item_id', 'starting_bid', 'bid_difference', 'end_time'
];

  public function item(){
    return $this->belongsTo('App\Item', 'item_id');
  }
}
