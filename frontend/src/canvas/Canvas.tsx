import { useEffect, useState } from 'react'
import styles from './canvas.module.css'

function Canvas({ coords, setCoords }) {
  const [selectedGate, setSelectedGate] = useState(0)
  const [placedGates, setPlacedGates] = useState([])

  const gateImages = {
    1: 'and.svg',
    2: 'or.svg',
    3: 'not.svg',
    4: 'nand.svg',
    5: 'nor.svg',
    6: 'xor.svg',
    7: 'xnor.svg',
    8: 'input.svg',
  }

  useEffect(() => {
    const handleKeyDown = (e) => {
      if (e.key.toLowerCase() === 'g') {
        setSelectedGate((prev) => {
          const nextValue = prev >= 8 ? 0 : prev + 1
          console.log('New Gate Index:', nextValue)
          return nextValue
        })
      } else if (e.key === 'Escape') {
        setSelectedGate(0)
      }
    }

    window.addEventListener('keydown', handleKeyDown)
    return () => window.removeEventListener('keydown', handleKeyDown)
  }, []) // Keep this empty to avoid adding/removing listeners constantly

  const gates = placedGates.map((gate, index) => (
    <div
      key={index}
      className="logicgate"
      style={{
        position: 'absolute',
        left: gate.pos[0],
        top: gate.pos[1],
        transform: 'translate(-50%, -50%)',
      }}
    >
      <img src={gateImages[gate.type]} alt="gate" />
      <p>
        ({gate.pos[0]}, {gate.pos[1]})
      </p>
    </div>
  ))

  const activegate = (
    <>
      <div
        className="logicgate"
        style={{
          position: 'absolute',
          left: coords[0],
          top: coords[1],
          transform: 'translate(-50%, -50%)',
        }}
      >
        {selectedGate != 0 ? (
          <img src={gateImages[selectedGate]} alt="gate" />
        ) : (
          ''
        )}
      </div>
    </>
  )

  return (
    <div
      onMouseMove={(e) => {
        setCoords([e.clientX, e.clientY])
      }}
      className={styles.canvas}
      onMouseDown={(e) => {
        if (selectedGate != 0) {
          setPlacedGates([
            ...placedGates,
            { pos: [e.clientX, e.clientY], type: selectedGate },
          ])
        }
      }}
    >
      {gates}
      {activegate}
    </div>
  )
}

export default Canvas
