// ==UserScript==
// @name         Zhihu Shield
// @namespace    http://tampermonkey.net/
// @version      0.0.1
// @description  Shield information you don't want to see.
// @author       Ciyang
// @match        https://www.zhihu.com/*
// @match        http://www.zhihu.com/*
// @exclude      https://www.zhihu.com/people/*
// @exclude      http://www.zhihu.com/people/*
// @grant        none
// ==/UserScript==

'use strict';

(function () {
    let mRequest = (medth, href, fn) => {
        var xmlhttp = new XMLHttpRequest();
        xmlhttp.open(medth, href, true);
        xmlhttp.onreadystatechange = () => {
            if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                console.log(xmlhttp);
                fn(xmlhttp.responseText);
            }
        };
        xmlhttp.send();
    }

    let userShieldMap = new Map();
    // [string, boolean]

    let getUserShielded = (username, href, callback) => {
        if (!userShieldMap.has(username)) {
            mRequest('get', href, (htmltext) => {
                let res = (htmltext.search('已屏蔽') !== -1);
                userShieldMap.set(username, res);
                callback(res);
            });
        } else {
            callback(userShieldMap.get(username));
        }
    }

    let timer;

    let checkShielded = () => {
        let userList = document.getElementsByClassName('UserLink-link');
        for (const user of userList) {
            if (user.innerText && user.href) {
                (userLinkElement => {
                    let url = new URL(userLinkElement.href, window.location.href);
                    getUserShielded(userLinkElement.innerText, url.href, res => {
                        if (res) {
                            let addCard = userLinkElement;
                            while (addCard.className.search('Card') === -1) addCard = addCard.parentElement;
                            addCard.innerHTML = ["<p>回答者", userLinkElement.innerText, "被拉入黑名单</p>"].join('');
                            // addCard.remove();
                        }
                    });
                })(user);
            }
        }
    }

    window.addEventListener('load', (event) => {
        checkShielded();

        let moCallback = (mutationsList, observer) => {
            for (const mutation of mutationsList) {
                if (mutation.type == 'childList' && mutation.addedNodes && mutation.addedNodes.length) {
                    console.log('A child node has been added');
                    if (timer) clearTimeout(timer);
                    timer = setTimeout(checkShielded, 100);
                }
            }
        };

        let targetNode = document.getElementById('TopstoryContent');

        let config = { childList: true, subtree: true };

        let observer = new MutationObserver(moCallback);

        observer.observe(targetNode, config);
    });
})();