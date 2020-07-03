<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Action extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'action';

  protected $fillable = [
    'reason', 'date', 'moderator_id',
];



}
