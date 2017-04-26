function success(e, x, s) {
	var r = "";
	if (e != "") {
		for (var i = 0; i < e.length; i++) {
			if (i > 0)
				r = r + ",";
			r = r + e.charCodeAt(i);
		}
		log("midi data received: " + r, 2);
		for (var i = 0; i < e.length; i += 3) {
			if (e.charCodeAt(i) == 3) {
				if (e.charCodeAt(i + 1) == 1) {
					$("#dialvalue").val(e.charCodeAt(i + 2));
				}
			}
		}
	}
}

function poll() {
	$.ajax({
      url: "http://localhost:8889",
      data: "",
      success: success,
      dataType: "text",
    });
}

function log(t, e) {
	var id;
	
	switch (e) {
		case 1:
			id = "error";
			break;
		case 2:
			id = "poll";
			break;
		default:
			id = "debug";
	}
	
	$("#log").append("<li id=\"" + id + "\">" + t + "</li>");
}
