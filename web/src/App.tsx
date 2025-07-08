import { BrowserRouter, Route, Routes } from 'react-router-dom'
import './App.css'
import { RoomProvider } from './context/RoomContext'
import CreateRoom from './pages/CreateRoom'
import HomePage from './pages/Home'
import RoomPage from './pages/RoomPage'
import LoginPage from './pages/Login'
import { AuthProvider } from './context/AuthContext'

function App() {

  return (
    <BrowserRouter>
      <AuthProvider>
        <RoomProvider>

        <Routes>
          <Route path="/" element={<HomePage/>} />
          <Route path="/host" element={<CreateRoom />} />
          <Route path="/room/:roomId" element={<RoomPage/>} />
          <Route path='/login' element={<LoginPage/>} />
        </Routes>


        </RoomProvider>
      </AuthProvider>
    </BrowserRouter>
  )
}

export default App
