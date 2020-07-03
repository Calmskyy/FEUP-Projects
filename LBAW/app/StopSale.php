<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class StopSale extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'stop_sale';

  protected $primaryKey = 'action_id';

  protected $fillable = [
    'action_id', 'item_id',
];



}
