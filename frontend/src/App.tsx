import { useState } from 'react'
import './App.css'
import Toolbar from './toolbar/Toolbar.js'
import Canvas from './canvas/Canvas.js'

function App() {
  const [coords, setCoords] = useState([0, 0])

  return (
    <>
      <Toolbar coords={coords}></Toolbar>
      <Canvas coords={coords} setCoords={setCoords}></Canvas>
    </>
  )
}

export default App
