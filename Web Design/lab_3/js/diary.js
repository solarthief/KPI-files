

$(document).ready(function() {
   $("h1").click(function() {
     $('*').css('color','blue');
   });	
});

$("#createT").click(
function(){
    var f=document.createElement("form");
    f.type="text";
    f.value="MYTEX";
    $("body").append(f);
}
);