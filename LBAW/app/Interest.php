<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Interest extends Model
{
  protected $fillable = [
    'user_id', 'type'
];
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'interest';
  
  public function user(){
    return $this->belongsTo('App\User');
  }
}
