import React from 'react';
import ReactDOM from 'react-dom'
import MainAppComponent from './MainAppComponent'
// Needed for onTouchTap
import injectTapEventPlugin from 'react-tap-event-plugin'
injectTapEventPlugin()
ReactDOM.render(
	<MainAppComponent />, document.getElementById('app')
)
