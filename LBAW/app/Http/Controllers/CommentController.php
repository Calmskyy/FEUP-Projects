<?php

namespace App\Http\Controllers;

use App\Item;
use App\Comment;

use App\Action;
use App\DeleteComment;

use Illuminate\Http\Request;

// use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Auth;

class CommentController extends Controller
{

    public function mod_delete(Request $request, $id)
    {
      $comment = Comment::find($id);

      $this->authorize('mod_delete', $comment);

      $action = Action::create(['reason' => $request->reason ,
                                'moderator_id' => Auth::user()->getId(),
                                'date' => date("Y-m-d")]);

      $delete_comment = DeleteComment::create(['action_id' => $action['id'],
                                      'comment_id' => $comment['id']]);

      return redirect()->route('item', $comment->item['id']);
    }

    public function edit(Request $request, $id)
    {
      $comment = Comment::find($id);

      $this->authorize('update', $comment);

      $comment->update(['content' => $request->input('content')]);

      return redirect()->route('item', $comment->item['id']);
    }

    public function delete(Request $request, $id)
    {
      $comment = Comment::find($id);

      $this->authorize('update', $comment);

      Comment::where('id', $id)
      ->delete();

      return redirect()->route('item', $comment->item['id']);
    }

    public function insertComment(Request $request)
    {
      $user_id = $request->input('user_id');
      $item_id = $request->input('item_id');
      $content = $request->input('content');
      $date = date("Y-m-d");
      $deleted = false;

      Comment::create(['user_id' => $user_id,
      'item_id' => $item_id,
      'content' => $content,
      'date' => $date,
      'deleted' => false
      ]);
      return redirect()->route('item', $item_id);
    }

}
