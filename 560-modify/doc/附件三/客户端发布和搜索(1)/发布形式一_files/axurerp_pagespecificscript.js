﻿
var PageName = '发布形式一';
var PageId = 'd8db061f573a4819a8bdb875c899010b'
var PageUrl = '发布形式一.html'
document.title = '发布形式一';
var PageNotes = 
{
"pageName":"发布形式一",
"showNotesNames":"False"}
var $OnLoadVariable = '';

var $CSUM;

var hasQuery = false;
var query = window.location.hash.substring(1);
if (query.length > 0) hasQuery = true;
var vars = query.split("&");
for (var i = 0; i < vars.length; i++) {
    var pair = vars[i].split("=");
    if (pair[0].length > 0) eval("$" + pair[0] + " = decodeURIComponent(pair[1]);");
} 

if (hasQuery && $CSUM != 1) {
alert('Prototype Warning: The variable values were too long to pass to this page.\nIf you are using IE, using Firefox will support more data.');
}

function GetQuerystring() {
    return '#OnLoadVariable=' + encodeURIComponent($OnLoadVariable) + '&CSUM=1';
}

function PopulateVariables(value) {
    var d = new Date();
  value = value.replace(/\[\[OnLoadVariable\]\]/g, $OnLoadVariable);
  value = value.replace(/\[\[PageName\]\]/g, PageName);
  value = value.replace(/\[\[GenDay\]\]/g, '29');
  value = value.replace(/\[\[GenMonth\]\]/g, '4');
  value = value.replace(/\[\[GenMonthName\]\]/g, '四月');
  value = value.replace(/\[\[GenDayOfWeek\]\]/g, '星期五');
  value = value.replace(/\[\[GenYear\]\]/g, '2011');
  value = value.replace(/\[\[Day\]\]/g, d.getDate());
  value = value.replace(/\[\[Month\]\]/g, d.getMonth() + 1);
  value = value.replace(/\[\[MonthName\]\]/g, GetMonthString(d.getMonth()));
  value = value.replace(/\[\[DayOfWeek\]\]/g, GetDayString(d.getDay()));
  value = value.replace(/\[\[Year\]\]/g, d.getFullYear());
  return value;
}

function OnLoad(e) {

}

var u115 = document.getElementById('u115');
gv_vAlignTable['u115'] = 'center';
var u122 = document.getElementById('u122');
gv_vAlignTable['u122'] = 'top';
var u21 = document.getElementById('u21');

var u32 = document.getElementById('u32');
gv_vAlignTable['u32'] = 'top';
var u156 = document.getElementById('u156');

var u207 = document.getElementById('u207');

var u130 = document.getElementById('u130');

var u7 = document.getElementById('u7');

var u2 = document.getElementById('u2');
gv_vAlignTable['u2'] = 'top';
var u79 = document.getElementById('u79');

var u4 = document.getElementById('u4');
gv_vAlignTable['u4'] = 'center';
var u153 = document.getElementById('u153');

var u140 = document.getElementById('u140');

var u17 = document.getElementById('u17');

var u135 = document.getElementById('u135');

var u151 = document.getElementById('u151');

var u42 = document.getElementById('u42');
gv_vAlignTable['u42'] = 'center';
var u159 = document.getElementById('u159');
gv_vAlignTable['u159'] = 'top';
var u55 = document.getElementById('u55');
gv_vAlignTable['u55'] = 'center';
var u101 = document.getElementById('u101');

var u186 = document.getElementById('u186');
gv_vAlignTable['u186'] = 'center';
var u14 = document.getElementById('u14');

var u48 = document.getElementById('u48');

var u105 = document.getElementById('u105');

var u27 = document.getElementById('u27');

var u138 = document.getElementById('u138');

var u52 = document.getElementById('u52');

var u20 = document.getElementById('u20');

var u67 = document.getElementById('u67');
gv_vAlignTable['u67'] = 'center';
var u65 = document.getElementById('u65');
gv_vAlignTable['u65'] = 'top';
var u120 = document.getElementById('u120');
gv_vAlignTable['u120'] = 'top';
var u152 = document.getElementById('u152');
gv_vAlignTable['u152'] = 'center';
var u110 = document.getElementById('u110');

var u6 = document.getElementById('u6');

var u205 = document.getElementById('u205');
gv_vAlignTable['u205'] = 'center';
var u108 = document.getElementById('u108');

var u37 = document.getElementById('u37');
gv_vAlignTable['u37'] = 'center';
var u62 = document.getElementById('u62');
gv_vAlignTable['u62'] = 'center';
var u141 = document.getElementById('u141');
gv_vAlignTable['u141'] = 'center';
var u11 = document.getElementById('u11');

var u75 = document.getElementById('u75');
gv_vAlignTable['u75'] = 'center';
var u133 = document.getElementById('u133');
gv_vAlignTable['u133'] = 'top';
var u200 = document.getElementById('u200');

var u34 = document.getElementById('u34');

var u68 = document.getElementById('u68');

var u89 = document.getElementById('u89');

var u39 = document.getElementById('u39');

var u47 = document.getElementById('u47');
gv_vAlignTable['u47'] = 'top';
var u184 = document.getElementById('u184');
gv_vAlignTable['u184'] = 'top';
var u185 = document.getElementById('u185');

var u72 = document.getElementById('u72');
gv_vAlignTable['u72'] = 'center';
var u103 = document.getElementById('u103');

var u164 = document.getElementById('u164');

var u99 = document.getElementById('u99');

var u66 = document.getElementById('u66');

var u112 = document.getElementById('u112');

var u44 = document.getElementById('u44');
gv_vAlignTable['u44'] = 'top';
var u78 = document.getElementById('u78');
gv_vAlignTable['u78'] = 'top';
var u179 = document.getElementById('u179');
gv_vAlignTable['u179'] = 'top';
var u57 = document.getElementById('u57');
gv_vAlignTable['u57'] = 'top';
var u191 = document.getElementById('u191');

var u119 = document.getElementById('u119');
gv_vAlignTable['u119'] = 'center';
var u16 = document.getElementById('u16');

var u203 = document.getElementById('u203');

var u125 = document.getElementById('u125');

var u41 = document.getElementById('u41');

var u172 = document.getElementById('u172');
gv_vAlignTable['u172'] = 'center';
var u149 = document.getElementById('u149');
gv_vAlignTable['u149'] = 'center';
var u54 = document.getElementById('u54');

var u208 = document.getElementById('u208');

var u118 = document.getElementById('u118');

var u197 = document.getElementById('u197');

var u88 = document.getElementById('u88');
gv_vAlignTable['u88'] = 'top';
var u189 = document.getElementById('u189');
gv_vAlignTable['u189'] = 'center';
var u38 = document.getElementById('u38');

var u176 = document.getElementById('u176');

var u26 = document.getElementById('u26');
gv_vAlignTable['u26'] = 'center';
var u174 = document.getElementById('u174');

var u128 = document.getElementById('u128');
gv_vAlignTable['u128'] = 'top';
var u85 = document.getElementById('u85');
gv_vAlignTable['u85'] = 'top';
var u51 = document.getElementById('u51');
gv_vAlignTable['u51'] = 'center';
var u182 = document.getElementById('u182');

u182.style.cursor = 'pointer';
if (bIE) u182.attachEvent("onclick", Clicku182);
else u182.addEventListener("click", Clicku182, true);
function Clicku182(e)
{
windowEvent = e;


if (true) {

	self.location.href="搜索.html" + GetQuerystring();

}

}

var u10 = document.getElementById('u10');

var u100 = document.getElementById('u100');

var u23 = document.getElementById('u23');

var u144 = document.getElementById('u144');

var u202 = document.getElementById('u202');
gv_vAlignTable['u202'] = 'top';
var u166 = document.getElementById('u166');

var u82 = document.getElementById('u82');
gv_vAlignTable['u82'] = 'center';
var u36 = document.getElementById('u36');

var u30 = document.getElementById('u30');
gv_vAlignTable['u30'] = 'center';
var u95 = document.getElementById('u95');

var u61 = document.getElementById('u61');

var u195 = document.getElementById('u195');
gv_vAlignTable['u195'] = 'top';
var u116 = document.getElementById('u116');

var u158 = document.getElementById('u158');

var u74 = document.getElementById('u74');

var u123 = document.getElementById('u123');

var u114 = document.getElementById('u114');

var u33 = document.getElementById('u33');
gv_vAlignTable['u33'] = 'top';
var u160 = document.getElementById('u160');

var u157 = document.getElementById('u157');
gv_vAlignTable['u157'] = 'center';
var u92 = document.getElementById('u92');

var u46 = document.getElementById('u46');
gv_vAlignTable['u46'] = 'center';
var u126 = document.getElementById('u126');
gv_vAlignTable['u126'] = 'center';
var u71 = document.getElementById('u71');

var u181 = document.getElementById('u181');

u181.style.cursor = 'pointer';
if (bIE) u181.attachEvent("onclick", Clicku181);
else u181.addEventListener("click", Clicku181, true);
function Clicku181(e)
{
windowEvent = e;


if (true) {

	self.location.href="发布形式三.html" + GetQuerystring();

}

}

var u198 = document.getElementById('u198');
gv_vAlignTable['u198'] = 'center';
var u5 = document.getElementById('u5');
gv_vAlignTable['u5'] = 'top';
var u98 = document.getElementById('u98');
gv_vAlignTable['u98'] = 'top';
var u127 = document.getElementById('u127');

var u43 = document.getElementById('u43');
gv_vAlignTable['u43'] = 'top';
var u169 = document.getElementById('u169');

var u56 = document.getElementById('u56');
gv_vAlignTable['u56'] = 'top';
var u150 = document.getElementById('u150');
gv_vAlignTable['u150'] = 'top';
var u187 = document.getElementById('u187');

var u142 = document.getElementById('u142');

var u106 = document.getElementById('u106');

var u168 = document.getElementById('u168');
gv_vAlignTable['u168'] = 'top';
var u154 = document.getElementById('u154');
gv_vAlignTable['u154'] = 'center';
var u40 = document.getElementById('u40');

var u139 = document.getElementById('u139');
gv_vAlignTable['u139'] = 'center';
var u87 = document.getElementById('u87');
gv_vAlignTable['u87'] = 'center';
var u53 = document.getElementById('u53');
gv_vAlignTable['u53'] = 'center';
var u193 = document.getElementById('u193');

var u104 = document.getElementById('u104');

var u192 = document.getElementById('u192');
gv_vAlignTable['u192'] = 'center';
var u121 = document.getElementById('u121');
gv_vAlignTable['u121'] = 'top';
var u19 = document.getElementById('u19');

var u155 = document.getElementById('u155');
gv_vAlignTable['u155'] = 'top';
var u206 = document.getElementById('u206');

var u109 = document.getElementById('u109');

var u84 = document.getElementById('u84');

var u50 = document.getElementById('u50');

var u97 = document.getElementById('u97');
gv_vAlignTable['u97'] = 'top';
var u63 = document.getElementById('u63');

var u170 = document.getElementById('u170');
gv_vAlignTable['u170'] = 'top';
var u76 = document.getElementById('u76');

var u134 = document.getElementById('u134');
gv_vAlignTable['u134'] = 'top';
var u81 = document.getElementById('u81');

var u177 = document.getElementById('u177');
gv_vAlignTable['u177'] = 'center';
var u209 = document.getElementById('u209');
gv_vAlignTable['u209'] = 'center';
var u94 = document.getElementById('u94');
gv_vAlignTable['u94'] = 'top';
var u60 = document.getElementById('u60');
gv_vAlignTable['u60'] = 'top';
var u190 = document.getElementById('u190');

var u102 = document.getElementById('u102');
gv_vAlignTable['u102'] = 'top';
var u9 = document.getElementById('u9');
gv_vAlignTable['u9'] = 'top';
var u73 = document.getElementById('u73');
gv_vAlignTable['u73'] = 'top';
var u69 = document.getElementById('u69');
gv_vAlignTable['u69'] = 'top';
var u147 = document.getElementById('u147');
gv_vAlignTable['u147'] = 'top';
var u163 = document.getElementById('u163');
gv_vAlignTable['u163'] = 'top';
var u91 = document.getElementById('u91');
gv_vAlignTable['u91'] = 'top';
var u131 = document.getElementById('u131');

var u64 = document.getElementById('u64');
gv_vAlignTable['u64'] = 'center';
var u70 = document.getElementById('u70');

var u24 = document.getElementById('u24');
gv_vAlignTable['u24'] = 'top';
var u188 = document.getElementById('u188');

var u162 = document.getElementById('u162');
gv_vAlignTable['u162'] = 'center';
var u204 = document.getElementById('u204');

var u117 = document.getElementById('u117');
gv_vAlignTable['u117'] = 'center';
var u13 = document.getElementById('u13');
gv_vAlignTable['u13'] = 'top';
var u113 = document.getElementById('u113');
gv_vAlignTable['u113'] = 'top';
var u29 = document.getElementById('u29');

var u132 = document.getElementById('u132');
gv_vAlignTable['u132'] = 'center';
var u175 = document.getElementById('u175');
gv_vAlignTable['u175'] = 'top';
var u129 = document.getElementById('u129');

var u86 = document.getElementById('u86');

var u58 = document.getElementById('u58');

var u183 = document.getElementById('u183');

var u173 = document.getElementById('u173');
gv_vAlignTable['u173'] = 'top';
var u111 = document.getElementById('u111');
gv_vAlignTable['u111'] = 'top';
var u171 = document.getElementById('u171');

var u0 = document.getElementById('u0');

var u31 = document.getElementById('u31');
gv_vAlignTable['u31'] = 'top';
var u83 = document.getElementById('u83');
gv_vAlignTable['u83'] = 'top';
var u178 = document.getElementById('u178');
gv_vAlignTable['u178'] = 'top';
var u8 = document.getElementById('u8');
gv_vAlignTable['u8'] = 'top';
var u3 = document.getElementById('u3');

var u96 = document.getElementById('u96');

var u146 = document.getElementById('u146');
gv_vAlignTable['u146'] = 'top';
var u196 = document.getElementById('u196');
gv_vAlignTable['u196'] = 'top';
var u15 = document.getElementById('u15');

var u49 = document.getElementById('u49');
gv_vAlignTable['u49'] = 'center';
var u124 = document.getElementById('u124');
gv_vAlignTable['u124'] = 'center';
var u80 = document.getElementById('u80');
gv_vAlignTable['u80'] = 'top';
var u1 = document.getElementById('u1');
gv_vAlignTable['u1'] = 'center';
var u148 = document.getElementById('u148');

var u93 = document.getElementById('u93');
gv_vAlignTable['u93'] = 'center';
var u167 = document.getElementById('u167');
gv_vAlignTable['u167'] = 'center';
var u145 = document.getElementById('u145');
gv_vAlignTable['u145'] = 'center';
var u12 = document.getElementById('u12');

var u201 = document.getElementById('u201');
gv_vAlignTable['u201'] = 'center';
var u165 = document.getElementById('u165');
gv_vAlignTable['u165'] = 'center';
var u199 = document.getElementById('u199');
gv_vAlignTable['u199'] = 'top';
var u25 = document.getElementById('u25');

var u59 = document.getElementById('u59');
gv_vAlignTable['u59'] = 'center';
var u137 = document.getElementById('u137');
gv_vAlignTable['u137'] = 'top';
var u90 = document.getElementById('u90');
gv_vAlignTable['u90'] = 'center';
var u18 = document.getElementById('u18');
gv_vAlignTable['u18'] = 'top';
var u161 = document.getElementById('u161');

var u45 = document.getElementById('u45');

var u77 = document.getElementById('u77');
gv_vAlignTable['u77'] = 'center';
var u22 = document.getElementById('u22');
gv_vAlignTable['u22'] = 'top';
var u143 = document.getElementById('u143');
gv_vAlignTable['u143'] = 'center';
var u107 = document.getElementById('u107');
gv_vAlignTable['u107'] = 'top';
var u35 = document.getElementById('u35');
gv_vAlignTable['u35'] = 'center';
var u136 = document.getElementById('u136');
gv_vAlignTable['u136'] = 'center';
var u180 = document.getElementById('u180');

u180.style.cursor = 'pointer';
if (bIE) u180.attachEvent("onclick", Clicku180);
else u180.addEventListener("click", Clicku180, true);
function Clicku180(e)
{
windowEvent = e;


if (true) {

	self.location.href="发布形式二.html" + GetQuerystring();

}

}

var u28 = document.getElementById('u28');
gv_vAlignTable['u28'] = 'center';
var u194 = document.getElementById('u194');
gv_vAlignTable['u194'] = 'center';
if (window.OnLoad) OnLoad();
