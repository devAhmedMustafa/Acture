import { BrowserRouter, Route, Routes } from 'react-router-dom'
import './App.css'
import { RoomProvider } from './contexts/RoomContext'
import CreateRoom from './pages/CreateRoom'
import HomePage from './pages/Home'
import RoomPage from './pages/RoomPage'
import LoginPage from './pages/Login'
import { AuthProvider } from './contexts/AuthContext'
import ProtectedRoute from './pages/ProtectedRoute'

function App() {

  return (
    <BrowserRouter>
      <AuthProvider>
        <RoomProvider>

        <Routes>
          <Route path="/" element={
            <ProtectedRoute>
              <HomePage/>
            </ProtectedRoute>
            } />
          <Route path="/host" element={
            <ProtectedRoute>
              <CreateRoom/>
            </ProtectedRoute>
            } />
          <Route path="/room/:roomId" element={
            <ProtectedRoute>
              <RoomPage/>
            </ProtectedRoute>
            } />
          <Route path='/login' element={<LoginPage/>} />
        </Routes>


        </RoomProvider>
      </AuthProvider>
    </BrowserRouter>
  )
}

export default App
