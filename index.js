const API_KEY = 'AIzaSyAqVpsr-Mhl_OyS1x9Oc9OPDRK9si1hr3M';
const CLIENT_ID = '184819840351-2lau0b3d1v2ajm1pf8pso14aim8acj5l.apps.googleusercontent.com';
const SCOPES = 'https://www.googleapis.com/auth/calendar.readonly';
var DISCOVERY_DOCS = ['https://www.googleapis.com/discovery/v1/apis/calendar/v3/rest'];

var btn = $("#btn");
var calendar = $("#calendar");
var notice = $("#notice");
var isSignin = false;



function initGapi() {
	gapi.client.init({
          apiKey: API_KEY,
          clientId: CLIENT_ID,
          discoveryDocs: DISCOVERY_DOCS,
          scope: SCOPES
        }).then(function () {
        	btn.on("click", () => {
        		if (isSignin) {
        			gapi.auth2.getAuthInstance().signOut();
        		} else {
        			gapi.auth2.getAuthInstance().signIn({
        				prompt: 'consent'
        			});
        		}
        	})
        	loginStateChange();
        	gapi.auth2.getAuthInstance().isSignedIn.listen(loginStateChange);
        	btn.show();
        }).catch(() => {});
}

function listEvents(start, end, timezone, cb) {
	var timeMin = (new Date(start._i)).toISOString();
	var timeMax = (new Date(end._i)).toISOString();
	gapi.client.calendar.events.list({
		  'calendarId': 'primary',
		  'timeMin': timeMin,
		  'timeMax': timeMax,
		  'showDeleted': false,
		  'singleEvents': false,
		  'orderBy': 'updated'
     }).then((response) => {
     	var events = response.result.items || [];
     	events.forEach((event) => {
     		event.title = event.summary;
     		event.start = event.start && event.start.date;
     		event.end = event.end && event.end.date;
     	})
     	cb(events);
     })
}

function loginStateChange() {
	isSignin = gapi.auth2.getAuthInstance().isSignedIn.get();
	if (!isSignin) {
		btn.text('sign in');
		notice.show();
		cal.fullCalendar('removeEventSource', listEvents);
	} else {
		notice.hide();
		btn.text('sign out');
		cal.fullCalendar('addEventSource', listEvents);
	}
}

gapi.load('client:auth2', initGapi);
var cal = calendar.fullCalendar({
	eventClick: (event) => {
		window.open(event.htmlLink, '_blank', 'width=700,height=600');
	}
});
