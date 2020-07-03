<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class BanUser extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'ban_user';

  protected $primaryKey = 'action_id';

  protected $fillable = [
    'action_id', 'user_id',
];



}
