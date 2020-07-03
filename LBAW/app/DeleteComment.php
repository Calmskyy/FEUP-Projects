<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class DeleteComment extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'delete_comment';

  protected $primaryKey = 'action_id';

  protected $fillable = [
    'action_id', 'comment_id',
];



}
