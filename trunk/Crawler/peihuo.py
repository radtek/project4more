# -*- coding: utf-8 -*-
import urllib2, urllib
import cookielib

def getContentBetween(c, b, e):
    p1 = c.find(b)
    if ( p1 == -1 ):
        return ""
    p1 += len(b)
    p2 = c.find(e, p1)
    if ( p2 == -1 ):
        return c[p1:]
    return c[p1:p2]

def getInfo():
    print 'start...'
    proxy="http://proxy.jpn.hp.com:8080"
    opener = urllib2.build_opener(urllib2.ProxyHandler({'http':proxy}), urllib2.HTTPCookieProcessor())
    exheaders = [("User-Agent","Mozilla/5.0 (Windows NT 5.1; rv:8.0) Gecko/20100101 Firefox/8.0"),]
    opener.addheaders=exheaders
    body = (('username','609770847'), ('password','13291575026'))
    login_url = r'http://www.peihuo.cn/peihuo/public/login_in.asp'
    main = r'http://www.peihuo.cn'
    f = opener.open(login_url, urllib.urlencode(body))
    print 'login finished...'
    req = opener.open(main)
    page = bytes.decode(req.read(), 'GBK')
    username = getContentBetween(page, '<div style="float:right;line-height:20px">', '</div>')
    print username
    ps = getContentBetween(page, 'id="id_tab1"', '</div>').split('<ul>')
    results = []
    for p in ps:
        ls = p.split('</li><li>')
        for l in ls:
            r = {}
            r['url'] = getContentBetween(l, "href='", "'")
            r['content'] = getContentBetween(l, "target=_blank>", "</a>")
            results.append(r)

    for r in results:
        print r['url'] + '    ' + r['content']
    
getInfo()
