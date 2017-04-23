import React from 'react'
import ReactDOM from 'react-dom'
import ListItem from 'material-ui/List/ListItem'
import BubbleRight from './BubbleRight'
import TriangleRight from './TriangleRight'
class MessageRight extends React.Component {
  constructor() {
    super()
  }
  componentDidMount = () => {
    var userDOM = ReactDOM.findDOMNode(this)
    userDOM.scrollIntoView({block: "end", behavior: "smooth"})
    userDOM.blur()
  }
  render() {
    var color = this.props.color
    var name = this.props.name
    var time = this.props.time
    var text = this.props.text
    return (
      <ListItem ref='bubble' style={{textAlign: 'left'}} disabled={true}>
        <BubbleRight name={name} time={time} text={text} color={color}/>
        <TriangleRight color={color}/>
      </ListItem>
    )
  }
}
export default MessageRight
