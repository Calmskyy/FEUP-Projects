

    <div class="row search-item pt-3 px-3">
        <div class="m-2 search-item-image">
            @if (count($item_auction->item->imagesItem) > 0)
                <a href="{{'./item/' . $item_auction->item['id']}}"><img src="{{asset('/images/items/' . $item_auction->item->imagesItem[0]->image['url'])}}" height="250" width="250" class="img-responsive"></a>
            @else
                <a href="{{'./item/' . $item_auction->item['id']}}"><img src="{{asset('/images/items/default.jpg')}}" height="250" width="250" class="img-responsive"></a>
            @endif
        </div>
        <div class="col py-3">
            <h4>{{ $item_auction->item['title']}}</h4>
            <h5 class="search-item-description">{{$item_auction->item['description']}}</h5>
            
            <div class="my-4">
              <span>Highest bid:</span>
              <h5 class="my-1">{{ !is_null($item_auction->current_bid) ? $item_auction->current_bid : "---" }}$</h5>
            </div>

            <div class="my-4">
                <h6>{{ $item_auction->item->owner['name'] }}</h6>
                @for ($i = 0; $i < $item_auction->item->owner['reputation']; $i++)
                    <span class="fa fa-star checked"></span>
                @endfor
                @for (; $i < 5; $i++)
                    <span class="fa fa-star"></span>
                @endfor
                <span class="mx-1">{{$item_auction->item->owner['reputation']}}</span>
            </div>
            
        </div>
    </div>

    <hr>

