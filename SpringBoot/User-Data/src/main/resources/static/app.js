var stomp = null;

function setup(check)
{
	$("#connect").prop("disabled",check);
	$("#disconnect").prop("disabled",!check);
	if(check)
	{
		$("#conversation").show();
	}
	else {
		$("#conversation").hide();	
	}
	$("#greetings").html("");
}

function connect()
{
	var socket = new SockJS('/Uweb');
	stomp = Stomp.over(socket);
	stomp.connect(
	{},
	function(temp){
	setup(true);	
	stomp.subscribe('/topic/greet',function (name) {
		showName(JSON.parse(name.body).content);
	});
	});

}

function disconnect() {
	if(stomp !== null)
	{
		stomp.disconnect();	
	}
	setup(false);
}

function sendName() {
	var data = JSON.stringify
	({
		"id"       : id,
		"username" : String(username),
		"password" : String(password),
		"age"      : age,
		"name"     : String(name)
	});

	stompClient.send("/app/hello", data);
}

function showName(temp) {
	$("#greeting").append("<tr><td>" + message + "</td></tr>");
}

$(function () {
   /* $("form").on('submit', function (e) {
        e.preventDefault();
    });*/
    $( "#connect" ).click(function() { connect(); });
    $( "#disconnect" ).click(function() { disconnect(); });
    $( "#Submit" ).click(function() { sendName(); });
});

