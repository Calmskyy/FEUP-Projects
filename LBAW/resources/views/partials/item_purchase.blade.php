<div class="row search-item pt-3 px-3">
        <div class="m-2 search-item-image">
            @if (count($item_purchase->item->imagesItem) > 0)
                <a href="{{'./item/' . $item_purchase->item['id']}}"><img src="{{asset('/images/items/' . $item_purchase->item->imagesItem[0]->image['url'])}}" height="250" width="250" class="img-responsive"></a>
            @else
                <a href="{{'./item/' . $item_purchase->item['id']}}"><img src="{{asset('/images/items/default.jpg')}}" height="250" width="250" class="img-responsive"></a>
            @endif
        </div>
        <div class="col py-3">
            <h4>{{ $item_purchase->item['title']}}</h4>
            <h5 class="search-item-description">{{$item_purchase->item['description']}}</h5>
            
            <div class="my-4">
                <span>Price:</span>
                <h5 class="my-1">{{ $item_purchase['price'] }}$</h5>
            </div>

            <div class="my-4">
                <h6>{{ $item_purchase->item->owner['name'] }}</h6>
                @for ($i = 0; $i < $item_purchase->item->owner['reputation']; $i++)
                    <span class="fa fa-star checked"></span>
                @endfor
                @for (; $i < 5; $i++)
                    <span class="fa fa-star"></span>
                @endfor
                <span class="mx-1">{{$item_purchase->item->owner['reputation']}}</span>
            </div>
            
        </div>
</div>

<hr>