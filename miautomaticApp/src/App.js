import React from 'react';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import { ThemeProvider } from '@mui/material/styles';
import theme from './styles/theme';
import Login from './pages/Login';
import Cadastro from './pages/Cadastro';
import Principal from './pages/Principal';
import Configuracao from './pages/Configuracao';

const App = () => {
  return (
    <ThemeProvider theme={theme}>
    <Router>
      <Routes>
        <Route path="/" element={<Login />} />
        <Route path="/principal" element={<Principal />} />
        <Route path="/configuracao" element={<Configuracao />} />
        <Route path="/cadastro" element={<Cadastro />} />
      </Routes>
    </Router>
    </ThemeProvider>
  );
};

export default App;