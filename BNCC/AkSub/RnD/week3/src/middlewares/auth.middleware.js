const jwt = require('jsonwebtoken');
const { sendError } = require('../utils/response');

const verifyToken = (req, res, next) => {
  const authHeader = req.headers['authorization'];

  if (!authHeader || !authHeader.startsWith('Bearer ')) {
    return sendError(res, 401, 'Token tidak ditemukan. Silakan login terlebih dahulu.');
  }

  const token = authHeader.split(' ')[1];

  try {
    const decoded = jwt.verify(token, process.env.JWT_SECRET);
    req.user = decoded;
    next();
  } catch (err) {
    return sendError(res, 401, 'Token tidak valid atau sudah expired.');
  }
};

const authorizeRoles = (...roles) => {
  return (req, res, next) => {
    if (!roles.includes(req.user.role)) {
      return sendError(res, 403, 'Akses ditolak. Kamu tidak memiliki izin untuk endpoint ini.');
    }
    next();
  };
};

module.exports = { verifyToken, authorizeRoles };