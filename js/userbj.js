TimeInterval = 100 * 1000

a = [
	"background.jpg"
];

console.log("loaded userbj.js");
var obj = document.body;
temp = obj.style.cssText;
var pos = -1;
changeBackground = function(){
    pos = parseInt(Math.random() * a.length);
    console.log(pos);
    obj.style.cssText = temp + "background: url(/images/" + a[pos] + "); background-repeat: no-repeat; background-attachment:fixed; background-size: cover; opacity: 0.92;"
    console.log(obj.style.cssText);
};
changeBackground();
setInterval(changeBackground, TimeInterval);
