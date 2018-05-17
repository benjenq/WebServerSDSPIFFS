//Button
$("#btnLed").click(function () {
    pushButton('/buildled');
});

/* API & Function */
function pushButton(apiurl) {
    //console.log(apiurl);
    $.ajax({
        url: apiurl,
        method: 'GET',
        cache: false,
        dataType: 'json',
        timeout: 1000,
        success: statusSuccess
    }).done(function (result) {
        if (console && console.log) {
            console.log("Sample of data:", result);
        }
    }).always(function () {


    }).statusCode({
        404: function () {
            alert('404: Not Found');
        },
        403: function () {
            alert('403: Forbidden');
        }

    }).fail(function (jqXHR, statustext, message) {
        alert('fail: |' + jqXHR.status + '|' + statustext + '|' + message);
    });
}

function statusSuccess(data) {
    console.log(data);
}

function getMcuName(apiurl) {
    //console.log(apiurl);
    $("#loading").hide;
    $("#loading").fadeIn(1000);
    $.ajax({
        url: apiurl,
        method: 'GET',
        cache: false,
        dataType: 'json',
        timeout: 16000
    }).done(function (result) {
        console.log('ajax done');
        $.each(result, function (key, val) {
            if (key === 'code') {
                
            } else if (key === 'result') {
                $("#mcuTitle").text(val + ' Built-In LED Control');
                $("title").text(val + ' Built-In LED Control');
            }
        });
    }).always(function () {
        console.log('ajax always');
        $("#loading").fadeOut(270);
    }).statusCode({
        404: function () {
            alert('404: Not Found');
        },
        403: function () {
            alert('403: Forbidden');
        }

    }).fail(function (jqXHR, statustext, message) {
        console.log('fail: |' + jqXHR.status + '|' + statustext + '|' + message);
        //$("button").prop('disabled', true);
        $("#mcuTitle").text('ESP - NOT Connected');
        $("title").text('ESP - NOT Connected');
    });
};

$(document).ready(function () {
    getMcuName('/mcuname');
});
