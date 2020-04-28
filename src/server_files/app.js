var ws;
var textArea;
var isShouldBeAnImage;
var isHasOldChild;
var oldChild;


$(function begin() {
    $('#id_form_get_list_ports').click(function onClick(e) {
        ws.send("GET_LIST_PORTS");
        textArea.text("");
        isShouldBeAnImage = false;
    })

    $('#id_form_get_auto_detect').click(function onClick(e) {
        ws.send("GET_AUTO_DETECT");
        textArea.text("");
        isShouldBeAnImage = false;
    })

    $('#id_form_get_summary').click(function onClick(e) {
        ws.send("GET_SUMMARY");
        textArea.text("");
        isShouldBeAnImage = false;
    })

    $('#id_form_get_list_files').click(function onClick(e) {
        ws.send("GET_LIST_FILES");
        textArea.text("");
        isShouldBeAnImage = false;
    })

    $('#id_form_get_now_photo').click(function onClick(e) {
        ws.send("GET_NOW_PHOTO");
        textArea.text("");
        isShouldBeAnImage = true;
    })

    isShouldBeAnImage = false;
    isHasOldChild = false;
    textArea = $('#message-area');
    ws = new WebSocket('ws://' + document.location.host + '/cam_project_2', ['string', 'foo']);

    ws.onopen = function () {
        console.log('onopen');
    };

    ws.onclose = function () {
    };

    ws.onmessage = function (message) {
        if ("HERE SHOULD BE A PHOTO" === message.data)
            isShouldBeAnImage = true;
        if (isShouldBeAnImage === true && "HERE SHOULD BE A PHOTO" !== message.data) {
            var image = new Image(640, 480);
            image.src = 'data:image/jpeg;base64,' + message.data;
            if (isHasOldChild === true)
                document.body.removeChild(oldChild);
            else
                isHasOldChild = true;
            document.body.appendChild(image);
            oldChild = image;
            isShouldBeAnImage = false;
        } else {
            textArea.text(textArea.text() + message.data);
        }
    };

    ws.onerror = function (error) {
    };
});
