// ==UserScript==
// @name         Luogu Unlimited Benben
// @version      1.0.0
// @description  Unlimited viewing of benben on any web page in Luogu
// @author       Ciyang
// @match        https://www.luogu.org/*
// @match        http://www.luogu.org/*
// ==/UserScript==
'use strict';

var version = "1.0.0", author = "Ciyang", blog = "https://xciyang.github.io/";
document.onkeydown = function (event) { if (event.keyCode == 113) mainfunc(); };
function mainfunc() {
    if (removek()) return;
    if (document.readyState == "complete") {
        var xmlHttp, xmlDoc;
        if (window.XMLHttpRequest) {// code for IE7, Firefox, Opera, etc.
            xmlHttp = new XMLHttpRequest();
        }
        else if (window.ActiveXObject) {// code for IE6, IE5
            xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
        }
        xmlHttp.open("GET", "https://www.luogu.org/feed/watching", false);
        xmlHttp.send(null);
        xmlDoc = xmlHttp.responseText;

        var newElement = document.createElement("div");
        newElement.id = "CiyangBenben";
        newElement.style.height = "50%";
        newElement.style.overflowX = "auto";
        newElement.style.overflowY = "scroll";
        newElement.style.left = "20%";
        newElement.style.backgroundColor = "#000";
        newElement.innerHTML += "<div class=\"lg-article\"><div class=\"am-form-group am-form\"><textarea rows=\"3\" id=\"feed-content\"></textarea></div><button class=\"am-btn am-btn-danger am-btn-sm\" id=\"feed-submit\">发射犇犇</button></div>"
        newElement.innerHTML += "<link rel=\"stylesheet\" href=\"https://cdn.luogu.com.cn/css/luogu3.css?ver=20190102\">";
        newElement.innerHTML += "<link rel=\"stylesheet\" href=\"https://cdn.luogu.com.cn/css/amazeui.min.css\">";
        newElement.innerHTML += xmlDoc;
        newElement.style.position = "fixed";
        var appElement = document.getElementById('app');
        appElement.appendChild(newElement);
    }
    return;
};
function removek() {
    var benben = document.getElementById("CiyangBenben");
    if (benben) {
        benben.parentNode.removeChild(benben);
        return true;
    }
    return false;
}
console.info("[Luogu Unlimited Benben]已加载成功,版本:" + version + ",作者:" + author + ",博客地址:" + blog);
