// ==UserScript==
// @name         Luogu Quick Searcher
// @version      10.0.0
// @description  Quick problems search in luogu~
// @author       Ciyang
// @match        https://www.luogu.org/*
// @match        http://www.luogu.org/*
// @grant        GM_getValue
// @grant        GM_setValue
// ==/UserScript==
'use strict';

var version = "10.0.0", author = "Ciyang", blog = "https://xciyang.github.io/";
var hstr = "<div class='am-topbar-form am-topbar-right am-form-inline lg-hide'><div class='am-input-group am-input-group-secondary am-input-group-sm'><input type='text' id='topbar-search-text' class='am-form-field am-input-sm am-radius' placeholder='题目搜索'><a class='am-input-group-label' id='topbar-search'><span class='am-icon-search'></span></a></div></div>";
var dUrl = GM_getValue("default_way");
document.onkeydown = function (event) { if (event.keyCode == 112) mainfunc(); };
function mainfunc() {
    if (removek()) return;
    if (document.readyState == "complete") {
        var newElement = document.createElement("div");
        newElement.id = "CiyangSearch";
        newElement.className = "search-wrap show";
        newElement.innerHTML = "<input type = 'text'> | <a><i class = 'fas fa-search'></i></a> | <i class= 'fa fa-cog'></i>";
        newElement.style.position = "fixed";
        newElement.style.zIndex = "2";
        newElement.style.top = "10%";
        newElement.style.left = "30%";
        newElement.style.width = "240px";
        newElement.style.backgroundColor = "rgb(128,128,128)";
        var appElement = document.getElementById('app');
        appElement.appendChild(newElement);
        newElement.children[0].onkeydown = function (event) {
            if (event.keyCode == 13) {
                var str = this.value;
                if (str.length == 0) return;
                if (str[0] == '#') pound_url(str.substring(1, str.length));
                else default_url(str);
            }
            return;
        };
        newElement.children[1].onclick = function () {
            var str = newElement.children[0].value;
            if (str.length == 0) return;
            if (str[0] == '#') pound_url(str.substring(1, str.length));
            else default_url(str);
            return;
        };
        newElement.children[2].onclick = function () { setLink(); };
        newElement.children[0].focus();
    }
    return;
};

function removek() {
    var search = document.getElementById("CiyangSearch");
    if (search) {
        search.parentNode.removeChild(search);
        return true;
    }
    return false;
}
function judegeProblem(str) {
    if (str.match(/AT[0-9]{1,4}/) == str) return true;
    if (str.match(/CF[0-9]{1,4}[A-Z][0-9]{0,1}/) == str) return true;
    if (str.match(/SP[0-9]{1,5}/) == str) return true;
    if (str.match(/P[0-9]{4}/) == str) return true;
    if (str.match(/UVA[0-9]{1,5}/) == str) return true;
    if (str.match(/U[0-9]{1,6}/) == str) return true;
    if (str.match(/T[0-9]{1,6}/) == str) return true;
    return false;
}
function pound_url(str) {
    if (str.length == 0) return;
    if (judegeProblem(str)) go(!dUrl, '/problemnew/show/' + str);
    else go(!dUrl, '/problem/list?keyword=' + str);
    return;
}
function default_url(str) {
    if (str.length == 0) return;
    if (judegeProblem(str)) go(dUrl, '/problemnew/show/' + str);
    else go(dUrl, '/problem/list?keyword=' + str);
    return;
}
function go(k, url) {
    if (k == 0) window.location = url;
    else window.open(url);
    removek();
}
function setLink() {
    var defaultWay = prompt("请输入首选打开网页方式，1 为新标签页，0为从当前页跳转。当前为" + dUrl + "，搜索先输入#可使用优先级低的方式。");
    if (defaultWay == null) return;
    if (defaultWay != "0" && defaultWay != "1") {
        alert("您的输入有误");
        return;
    }
    GM_setValue("default_way", defaultWay);
    location.reload();
}

console.info("[Luogu Quick Searcher]已加载成功,版本:" + version + ",作者:" + author + ",博客地址:" + blog);
