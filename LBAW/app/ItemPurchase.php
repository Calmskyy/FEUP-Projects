<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class ItemPurchase extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'purchase_item';

  protected $primaryKey = 'item_id';

  protected $fillable = [
    'item_id', 'price',
];

  public function item(){
    return $this->belongsTo('App\Item', 'item_id');
  }
}