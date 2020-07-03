<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Comment extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'comment';

  protected $fillable = [
    'user_id', 'item_id', 'content', 'date', 'deleted'
];

  public function item(){
    return $this->belongsTo('App\Item', 'item_id');
  }

  public function user(){
    return $this->belongsTo('App\User', 'user_id');
  }
}
