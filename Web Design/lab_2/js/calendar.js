var CONFIG = {
	'cssprefix'  : 'cal',
	'months'     : ['Січень','Лютий','Березень','Квітень','Травень','Червень','Липень','Серпень','Вересень','Жовтень','Листопад','Грудень'],
	'weekdays'   : ['Пн', 'Вт', 'Ср', 'Чт', 'Пт', 'Сб','Нд'],
	'longwdays'  : ['Понеділок','Вівторок','Середа','Четвер','П\'ятниця','Субота','Неділя',],
	'prevyear'   : 'Попередній Рік',
	'nextyear'   : 'Наступний Рік',
	'prevmonth'  : 'Попередній Місяць',
	'nextmonth'  : 'Наступний Місяць',
	'format'     : 'd/m/Y' 
};

var tokens = [
	 // A full numeric representation of a year, 4 digits
	{'t': 'Y', 'r': '19\\d{2}|20\\d{2}', 'p': function (d_date, n_value) { d_date.setFullYear(Number(n_value)); return d_date; }, 'g': function (d_date) { var n_year = d_date.getFullYear(); return n_year; }},
	 // Numeric representation of a month, with leading zeros
	{'t': 'm', 'r': '0?[1-9]|1[0-2]', 'p': function (d_date, n_value) { d_date.setMonth(Number(n_value) - 1); return d_date; }, 'g': function (d_date) { var n_month = d_date.getMonth() + 1; return (n_month < 10 ? '0' : '') + n_month }},
	// Day of the month, 2 digits with leading zeros
	{'t': 'd', 'r': '0?[1-9]|[12][0-9]|3[01]', 'p': function (d_date, n_value) { d_date.setDate(Number(n_value)); if (d_date.getDate() != n_value) d_date.setDate(0); return d_date }, 'g': function (d_date) { var n_date = d_date.getDate(); return (n_date < 10 ? '0' : '') + n_date; }},	
];

function f_GetHTML (d_date) {

	var e_input = f_GetInputs(true);
	if (!e_input) return;

	var s_pfx = CONFIG.cssprefix,
		s_format = CONFIG.format;
	// today from client date
	d_today = f_ResetTime(new Date());
	// selected date from input or today 
	d_selected = new Date(d_today);
	
	// show calendar for passed or selected date
	d_date = d_date ? f_ResetTime(d_date) : new Date(d_selected);

	var d_firstDay = new Date(d_date);
	d_firstDay.setDate(1);
	d_firstDay.setDate(1 - (6 + d_firstDay.getDay()) % 7);

	var a_class, s_html = '<table id="' + s_pfx + 'Controls"><tbody><tr>'
		+ '<td id="' + s_pfx + 'PrevYear" ' + f_RelDate(d_date, -1, 'y') + ' title="' + CONFIG.prevyear + '"></td>'
		+ '<td id="' + s_pfx + 'PrevMonth"' + f_RelDate(d_date, -1) + ' title="' + CONFIG.prevmonth + '"></td><th>'
		+ CONFIG.months[d_date.getMonth()] + ' ' + d_date.getFullYear()
		+ '</th><td id="' + s_pfx + 'NextMonth"' + f_RelDate(d_date, 1) + ' title="' + CONFIG.nextmonth + '"></td>'
		+ '<td id="' + s_pfx + 'NextYear"' + f_RelDate(d_date, 1, 'y') + ' title="' + CONFIG.nextyear + '"></td>'
		+ '</tr></tbody></table><table id="' + s_pfx + 'Grid"><tbody><tr>';

	// print weekdays titles
	for (var i = 0; i < 7; i++)
		s_html += '<th>' + CONFIG.weekdays[i] + '</th>';
	s_html += '</tr>' ;

	// print calendar table
	var n_date, n_month, d_current = new Date(d_firstDay);
	while (d_current.getMonth() == d_date.getMonth() ||
		d_current.getMonth() == d_firstDay.getMonth()) {

		s_html +='<tr>';
		for (var n_wday = 0; n_wday < 7; n_wday++) {

			a_class = [];
			n_date  = d_current.getDate();
			n_month = d_current.getMonth();

			if (d_current.getMonth() != d_date.getMonth())
				a_class[a_class.length] = s_pfx + 'OtherMonth';
			if (d_current.getDay() == 0 || d_current.getDay() == 6)
				a_class[a_class.length] = s_pfx + 'Weekend';
			if (d_current.valueOf() == d_today.valueOf())
				a_class[a_class.length] = s_pfx + 'Today';
			if (d_current.valueOf() == d_selected.valueOf())
				a_class[a_class.length] = s_pfx + 'Selected';

			s_html += '<td' + f_RelDate(d_current) + (a_class.length ? ' class="' + a_class.join(' ') + '">' : '>') + n_date + '</td>';
			d_current.setDate(++n_date);
		}
		s_html +='</tr>';
	}
	s_html +='</tbody></table>';

	return s_html;
}

function f_RelDate (d_date, d_diff, s_units) {
	var s_units = (s_units == 'y' ? 'FullYear' : 'Month');
	var d_result = new Date(d_date);
	if (d_diff) {
		d_result['set' + s_units](d_date['get' + s_units]() + d_diff);
		if (d_result.getDate() != d_date.getDate())
			d_result.setDate(0);
	}
	return ' onclick="f_Update(' + d_result.valueOf() + (d_diff ? ',1' : '') + ')"';
}

function f_ResetTime (d_date) {
	d_date.setMilliseconds(0);
	d_date.setSeconds(0);
	d_date.setMinutes(0);
	d_date.setHours(12);
	return d_date;
}

// closes calendar and returns all inputs to default state
function f_Cancel () {	
	var s_pfx = CONFIG.cssprefix;
	var e_cal = document.getElementById(s_pfx);
	if (e_cal)
		e_cal.style.visibility = '';
	var a_inputs = f_GetInputs();
	for (var n = 0; n < a_inputs.length; n++)
		f_RemoveClass(a_inputs[n], s_pfx + 'Active');
}

function f_Update (n_date, b_keepOpen) {
	var e_input = f_GetInputs(true);
	if (!e_input) return;
	
	d_date = new Date(n_date);
	var s_pfx = CONFIG.cssprefix;

	if (b_keepOpen) {
		var e_cal = document.getElementById(s_pfx);
		if (!e_cal || e_cal.style.visibility != 'visible') return;
		e_cal.innerHTML = f_GetHTML(d_date, e_input);
	}
	else {
		e_input.value = f_GenerateDate(d_date, CONFIG.format);
		f_Cancel();
	}
}

function f_OnClick () {

	// see if already opened
	var s_pfx = CONFIG.cssprefix;
	var s_activeClass = s_pfx + 'Active';
	var b_close = f_HasClass(this, s_activeClass);

	// close all calendars
	f_Cancel();
	if (b_close) return;

	// get position of input
	f_AddClass(this, s_activeClass);
	
	var n_left = f_getPosition (this, 'Left'),
		n_top  = f_getPosition (this, 'Top') + this.offsetHeight;

	var e_cal = document.getElementById(s_pfx);
	if (!e_cal) {
		e_cal = document.createElement('div');
		e_cal.onselectstart = function () { return false };
		e_cal.id = s_pfx;
		document.getElementsByTagName("body").item(0).appendChild(e_cal);
	}
	e_cal.innerHTML = f_GetHTML(null);
	e_cal.style.top = n_top + 'px';
	e_cal.style.left = (n_left + this.offsetWidth - e_cal.offsetWidth) + 'px';
	e_cal.style.visibility = 'visible';
}



function f_GenerateDate (d_date, s_format) {
	
	var s_char, s_date = '';
	for (var n = 0; n < s_format.length; n++) {
		s_char = s_format.charAt(n);
		s_date += tokens_id[s_char] ? tokens_id[s_char]['g'](d_date) : s_char;
	}
	return s_date;
}

function f_GetInputs (b_active) {

	var a_inputs = document.getElementsByTagName('input'),
		e_input, s_rel, a_result = [];

	for (n = 0; n < a_inputs.length; n++) {

		e_input = a_inputs[n];
		if (!e_input.type || e_input.type != 'text')
			continue;

		if (!f_HasClass(e_input, 'cal'))
			continue;

		if (b_active && f_HasClass(e_input, CONFIG.cssprefix + 'Active'))
			return e_input;

		a_result[a_result.length] = e_input;
	}
	return b_active ? null : a_result;
}

function f_HasClass (e_elem, s_class) {
	var s_classes = e_elem.className;
	if (!s_classes)
		return false;
	var a_classes = s_classes.split(' ');
	for (var n = 0; n < a_classes.length; n++)
		if (a_classes[n] == s_class)
			return true;
	return false;
}

function f_AddClass (e_elem, s_class) {
	if (f_HasClass (e_elem, s_class))
		return;

	var s_classes = e_elem.className;
	e_elem.className = (s_classes ? s_classes + ' ' : '') + s_class;
}

function f_RemoveClass (e_elem, s_class) {
	var s_classes = e_elem.className;
	if (!s_classes || s_classes.indexOf(s_class) == -1)
		return false;

	var a_classes = s_classes.split(' '),
		a_newClasses = [];

	for (var n = 0; n < a_classes.length; n++) {
		if (a_classes[n] == s_class)
			continue;
		a_newClasses[a_newClasses.length] = a_classes[n];
	}
	e_elem.className = a_newClasses.join(' ');
	return true;
}

function f_getPosition (e_elemRef, s_coord) {
	var n_pos = 0, n_offset,
		e_elem = e_elemRef;

	while (e_elem) {
		n_offset = e_elem["offset" + s_coord];
		n_pos += n_offset;
		e_elem = e_elem.offsetParent;
	}

	e_elem = e_elemRef;
	while (e_elem != document.body) {
		n_offset = e_elem["scroll" + s_coord];
		if (n_offset && e_elem.style.overflow == 'scroll')
			n_pos -= n_offset;
		e_elem = e_elem.parentNode;
	}
	return n_pos;
}

function f_Init () {
	
	if (!document.getElementsByTagName)
		return;

	var e_input, a_inputs = f_GetInputs();
	for (var n = 0; n < a_inputs.length; n++) {
		e_input = a_inputs[n];
		e_input.onclick = f_OnClick;
		f_AddClass(e_input, CONFIG.cssprefix + 'Input');
	}
	
	window.tokens_id = {};
	for (n = 0; n < tokens.length; n++)
		tokens_id[tokens[n]['t']] = tokens[n];
}

function f_AddOnload (f_func) {
	if (document.addEventListener) {
		window.addEventListener('load', f_func, false);
	}
	else if (window.attachEvent) {
		window.attachEvent('onload', f_func);
	}
	else {
		var f_onLoad = window.onload;
		if (typeof window.onload != 'function') {
			window.onload = f_func;
		}
		else {
			window.onload = function() {
				f_onLoad();
				f_func();
			}
		}
	}
}

f_AddOnload (f_Init);
