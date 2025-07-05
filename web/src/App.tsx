import { BrowserRouter, Route, Routes } from 'react-router-dom'
import './App.css'
import { RoomProvider } from './context/RoomContext'
import CreateRoom from './pages/CreateRoom'
import HomePage from './pages/Home'
import RoomPage from './pages/RoomPage'

function App() {

  return (
    <BrowserRouter>
      <RoomProvider>

      <Routes>
        <Route path="/" element={<HomePage/>} />
        <Route path="/host" element={<CreateRoom />} />
        <Route path="/room/:roomId" element={<RoomPage/>} />
      </Routes>

      </RoomProvider>
    </BrowserRouter>
  )
}

export default App
