import React from 'react'
import ReactDOM from 'react-dom'
import ListItem from 'material-ui/List/ListItem'
class User extends React.Component {
  constructor() {
    super()
  }
  componentDidMount = () => {
    var messageDOM = ReactDOM.findDOMNode(this)
    messageDOM.scrollIntoView({block: "end", behavior: "smooth"})
    messageDOM.blur()
  }
  render() {
    var name = this.props.name
    var color = this.props.color
    return (
      <ListItem ref='user' style={{textAlign: 'left', backgroundColor: color}} disabled={true}>
        <div>
          <span style={{fontSize:'smaller', fontWeight:'bold', color: 'white'}}>{name}</span>
        </div>
      </ListItem>
    )
  }
}
export default User
