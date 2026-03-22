const express = require('express');
const router = express.Router();
const controller = require('./news.controller');
const { verifyToken, authorizeRoles } = require('../../middlewares/auth.middleware');

router.get('/', controller.getAllNews);
router.post('/', verifyToken, authorizeRoles('writer', 'admin'), controller.createNews);
router.put('/:id', verifyToken, authorizeRoles('writer', 'admin'), controller.updateNews);
router.delete('/:id', verifyToken, authorizeRoles('writer', 'editor', 'admin'), controller.deleteNews);
router.patch('/:id/publish', verifyToken, authorizeRoles('editor'), controller.publishNews);

module.exports = router;