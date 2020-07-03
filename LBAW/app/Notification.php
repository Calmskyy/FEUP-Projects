<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Notification extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'notification';

  public function user(){
    return $this->belongsTo('App\User', 'user_id');
  }

  public function notificationItem(){
    return $this->hasOne('App\NotificationItem', 'notification_id');
  }

  public function notificationUser(){
    return $this->hasOne('App\NotificationUser', 'notification_id');
  }

}

// CREATE TABLE notification (
//     id          SERIAL PRIMARY KEY,
//     user_id     INTEGER REFERENCES "user" (id) 
//                         NOT NULL,
//     description TEXT    NOT NULL,
//     "date"        TIMESTAMP    NOT NULL
// );

// CREATE TABLE notification_item (
//   notification_id	INTEGER	REFERENCES notification (ID)
//   					NOT NULL,
//   item_id			INTEGER REFERENCES item (ID) NOT NULL
// );

// CREATE TABLE notification_user (
//   notification_id	INTEGER REFERENCES notification (ID)
//   					NOT NULL,
//   user_id			INTEGER REFERENCES "user" (ID) NOT NULL
// );