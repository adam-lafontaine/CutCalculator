import React from 'react'
const TriangleRight = (props) => {
  return (
    <div
      style={{content:"", /* triangle */
        position:'absolute',
        bottom:'-10px', /* value = - border-top-width - border-bottom-width */
        right: '50px', /* controls horizontal position */
        borderWidth: '10px 10px 0', /* vary these values to change the angle of the vertex */
        borderStyle: 'solid',
        borderColor: `${props.color} transparent`}} />
  )
}
export default TriangleRight
