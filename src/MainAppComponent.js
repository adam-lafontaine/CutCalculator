import React from 'react'
import MuiThemeProvider from 'material-ui/styles/MuiThemeProvider'
import UserInput from './comp/UserInput'

class MainAppComponent extends React.Component {
  constructor() {
    super()
    this.state = {
      showResults: false,
    }
  }

  componentDidMount() {



  }

  handleShowResults = (params) => {

  	//do stuff with params
    this.setState({showResults: true});
  }

  handleRestart = () => {

  }



  render() {
    return (
      <MuiThemeProvider>
        <div>

          {this.state.showResults == false &&
          <UserInput onShowResults={this.handleShowResults} />}
          {this.state.showResults == true &&
          <div/>}
        </div>
      </MuiThemeProvider>
    )
  }
}
export default MainAppComponent
