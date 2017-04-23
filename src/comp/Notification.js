import React from 'react';
const Notification = (props) => {

  return (
    <div style={{color: props.color}}>{props.text}</div>
  )
}
export default Notification
