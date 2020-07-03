<li class="notification-box {{ ($key % 2 == 1)? "bg-gray" : "" }}">
    @if (!is_null($notification->notificationItem))
        <a href="{{ route('item', $notification->notificationItem->item->getId()) }}">
    @elseif (!is_null($notification->notificationUser))
        <a href="{{ route('profile', $notification->notificationUser->user->getId()) }}">
    @else
        <a href="">
    @endif
        <div class="row">
            <div class="col-lg-3 col-sm-3 col-3 text-center">
                @if (!is_null($notification->notificationItem))
                    @if (count($notification->notificationItem->item->imagesItem) > 0)
                        <img class="w-50" src="{{asset('/images/items/' . $notification->notificationItem->item->imagesItem[0]->image['url'])}}" alt="arte"></img>
                    @else
                        <img class="w-50" id="image" src="{{asset('/images/items/default.jpg')}}" alt="arte"></img>
                    @endif
                @elseif (!is_null($notification->notificationUser))
                    @if (!is_null($notification->notificationUser->user->imageUser))
                        <img class="w-50" src="{{asset('/images/users/' . $notification->notificationUser->user->imageUser->image['url'])}}" alt="arte"></img>
                    @else
                        <img class="w-50" id="image" src="{{asset('/images/users/default.png')}}" alt="arte"></img>
                    @endif
                @endif
            </div>    
            <div class="col-lg-8 col-sm-8 col-8">
                @if (!is_null($notification->notificationItem))
                    <strong class="text-info">Item: {{$notification->notificationItem->item->title}}</strong>
                @elseif (!is_null($notification->notificationUser))
                    <strong class="text-info">User: {{$notification->notificationUser->user->name}}</strong>
                @else
                    <strong class="text-info">System</strong>
                @endif

                <div>
                {{ $notification->description }}
                </div>
                <small class="text-warning">{{ $notification->date }}</small>
            </div>    
        </div>
    </a>
</li>