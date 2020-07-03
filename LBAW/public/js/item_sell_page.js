let differenceInput = document.getElementById('difference-input');
let limitDateInput = document.getElementById('limit-date-input');
let limitHourInput = document.getElementById('limit-hour-input');

let differenceFormGroup = document.getElementById('difference-form-group');
let datesFormGroup = document.getElementById('dates-form-group');
let priceLabel = document.getElementById('price-label');

function changeSellType(selectObject) {
    var value = selectObject.value;

    if (value == "Sale") {
        differenceInput.required = false;
        limitDateInput.required = false;
        limitHourInput.required = false;
        differenceFormGroup.hidden = true;
        datesFormGroup.hidden = true;
        priceLabel.innerHTML = "Price";
    } else if (value == "Auction"){
        differenceInput.required = true;
        limitDateInput.required = true;
        limitHourInput.required = true;
        differenceFormGroup.hidden = false;
        datesFormGroup.hidden = false;
        priceLabel.innerHTML = "Starting Bid";
    }
    console.log(value);
}